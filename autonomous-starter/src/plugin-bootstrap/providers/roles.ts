import {
  ChannelType,
  createUniqueUuid,
  logger,
  type IAgentRuntime,
  type Memory,
  type Provider,
  type ProviderResult,
  type State,
  type UUID,
} from "@elizaos/core";

/**
 * A provider for retrieving and formatting the role hierarchy in a server.
 * @type {Provider}
 */
export const roleProvider: Provider = {
  name: "ROLES",
  description:
    "Roles in the server, default are OWNER, ADMIN and MEMBER (as well as NONE)",
  get: async (
    runtime: IAgentRuntime,
    message: Memory,
    state: State,
  ): Promise<ProviderResult> => {
    const room = state.data.room ?? (await runtime.getRoom(message.roomId));
    if (!room) {
      throw new Error("No room found");
    }

    if (room.type !== ChannelType.GROUP) {
      return {
        data: {
          roles: [],
        },
        values: {
          roles:
            "No access to role information in DMs, the role provider is only available in group scenarios.",
        },
        text: "No access to role information in DMs, the role provider is only available in group scenarios.",
      };
    }

    const serverId = room.serverId;

    if (!serverId) {
      throw new Error("No server ID found");
    }

    try {
      logger.info(`Using server ID: ${serverId}`);

      // Get world data instead of using cache
      const worldId = createUniqueUuid(runtime, serverId);
      const world = await runtime.getWorld(worldId);

      if (!world || !world.metadata?.ownership?.ownerId) {
        logger.info(
          `No ownership data found for server ${serverId}, initializing empty role hierarchy`,
        );
        return {
          data: {
            roles: [],
          },
          values: {
            roles: "No role information available for this server.",
          },
          text: "No role information available for this server.",
        };
      }
      // Get roles from world metadata
      const roles = world.metadata.roles || {};

      if (Object.keys(roles).length === 0) {
        logger.info(`No roles found for server ${serverId}`);
        return {
          data: {
            roles: [],
          },
          values: {
            roles: "No role information available for this server.",
          },
        };
      }

      logger.info(`Found ${Object.keys(roles).length} roles`);

      // Group users by role
      const owners: { name: string; username: string; names: string[] }[] = [];
      const admins: { name: string; username: string; names: string[] }[] = [];
      const members: { name: string; username: string; names: string[] }[] = [];

      // Process roles
      for (const entityId of Object.keys(roles) as UUID[]) {
        const userRole = roles[entityId];

        // get the user from the database
        const user = await runtime.getEntityById(entityId);

        const name = user.metadata[room.source]?.name;
        const username = user.metadata[room.source]?.username;
        const names = user.names;

        // Skip duplicates (we store both UUID and original ID)
        if (
          owners.some((owner) => owner.username === username) ||
          admins.some((admin) => admin.username === username) ||
          members.some((member) => member.username === username)
        ) {
          continue;
        }

        // Add to appropriate group
        switch (userRole) {
          case "OWNER":
            owners.push({ name, username, names });
            break;
          case "ADMIN":
            admins.push({ name, username, names });
            break;
          default:
            members.push({ name, username, names });
            break;
        }
      }

      // Format the response
      let response = "# Server Role Hierarchy\n\n";

      if (owners.length > 0) {
        response += "## Owners\n";
        owners.forEach((owner) => {
          response += `${owner.name} (${owner.names.join(", ")})\n`;
        });
        response += "\n";
      }

      if (admins.length > 0) {
        response += "## Administrators\n";
        admins.forEach((admin) => {
          response += `${admin.name} (${admin.names.join(", ")}) (${admin.username})\n`;
        });
        response += "\n";
      }

      if (members.length > 0) {
        response += "## Members\n";
        members.forEach((member) => {
          response += `${member.name} (${member.names.join(", ")}) (${member.username})\n`;
        });
      }

      return {
        data: {
          roles: response,
        },
        values: {
          roles: response,
        },
        text: response,
      };
    } catch (error) {
      logger.error("Error in role provider:", error);
      return {
        data: {
          roles: [],
        },
        values: {
          roles: "There was an error retrieving role information.",
        },
        text: "There was an error retrieving role information.",
      };
    }
  },
};

export default roleProvider;
