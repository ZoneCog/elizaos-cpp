#include <gtest/gtest.h>
#include <thread>
#include "elizaos/agentagenda.hpp"

using namespace elizaos;

class AgentAgendaTest : public ::testing::Test {
protected:
    void SetUp() override {
        agenda = std::make_unique<AgentAgenda>();
    }

    void TearDown() override {
        agenda->clearTasks();
        agenda.reset();
    }

    std::unique_ptr<AgentAgenda> agenda;
};

TEST_F(AgentAgendaTest, CreateBasicTask) {
    std::string goal = "Write comprehensive tests";
    
    auto task = agenda->createTask(goal);
    
    EXPECT_FALSE(task.id.empty());
    EXPECT_EQ(task.goal, goal);
    EXPECT_FALSE(task.plan.empty());
    EXPECT_FALSE(task.steps.empty());
    EXPECT_EQ(task.status, AgendaTaskStatus::IN_PROGRESS);
    EXPECT_TRUE(task.current);
}

TEST_F(AgentAgendaTest, CreateTaskWithCustomPlan) {
    std::string goal = "Complete project";
    std::string plan = "1. Analyze requirements 2. Design solution 3. Implement 4. Test";
    
    auto task = agenda->createTask(goal, plan);
    
    EXPECT_EQ(task.goal, goal);
    EXPECT_EQ(task.plan, plan);
    EXPECT_FALSE(task.steps.empty());
}

TEST_F(AgentAgendaTest, CreateTaskWithCustomSteps) {
    std::string goal = "Learn C++";
    std::string plan = "Systematic learning approach";
    std::vector<AgendaTaskStep> steps = {
        AgendaTaskStep("Read C++ basics", false),
        AgendaTaskStep("Practice coding", false),
        AgendaTaskStep("Build a project", false)
    };
    
    auto task = agenda->createTask(goal, plan, steps);
    
    EXPECT_EQ(task.goal, goal);
    EXPECT_EQ(task.plan, plan);
    EXPECT_EQ(task.steps.size(), 3);
    EXPECT_EQ(task.steps[0].content, "Read C++ basics");
    EXPECT_FALSE(task.steps[0].completed);
}

TEST_F(AgentAgendaTest, ListTasks) {
    // Create multiple tasks
    agenda->createTask("Task 1");
    agenda->createTask("Task 2");
    agenda->createTask("Task 3");
    
    auto tasks = agenda->listTasks(AgendaTaskStatus::IN_PROGRESS);
    
    EXPECT_EQ(tasks.size(), 3);
    
    // Check that only the last task is current
    int current_count = 0;
    for (const auto& task : tasks) {
        if (task.current) {
            current_count++;
        }
    }
    EXPECT_EQ(current_count, 1);
}

TEST_F(AgentAgendaTest, GetTaskById) {
    auto created_task = agenda->createTask("Find this task");
    
    auto retrieved_task = agenda->getTaskById(created_task.id);
    
    EXPECT_EQ(retrieved_task.id, created_task.id);
    EXPECT_EQ(retrieved_task.goal, "Find this task");
    
    // Test non-existent task
    auto empty_task = agenda->getTaskById("non-existent-id");
    EXPECT_TRUE(empty_task.id.empty());
}

TEST_F(AgentAgendaTest, FinishTask) {
    auto task = agenda->createTask("Task to complete");
    
    EXPECT_TRUE(agenda->finishTask(task.id));
    
    auto updated_task = agenda->getTaskById(task.id);
    EXPECT_EQ(updated_task.status, AgendaTaskStatus::COMPLETE);
    EXPECT_FALSE(updated_task.current); // Completed tasks are not current
    
    // Check that it's not in the in-progress list
    auto in_progress_tasks = agenda->listTasks(AgendaTaskStatus::IN_PROGRESS);
    bool found_in_progress = false;
    for (const auto& t : in_progress_tasks) {
        if (t.id == task.id) {
            found_in_progress = true;
            break;
        }
    }
    EXPECT_FALSE(found_in_progress);
}

TEST_F(AgentAgendaTest, CancelTask) {
    auto task = agenda->createTask("Task to cancel");
    
    EXPECT_TRUE(agenda->cancelTask(task.id));
    
    auto updated_task = agenda->getTaskById(task.id);
    EXPECT_EQ(updated_task.status, AgendaTaskStatus::CANCELLED);
    EXPECT_FALSE(updated_task.current);
}

TEST_F(AgentAgendaTest, DeleteTask) {
    auto task = agenda->createTask("Task to delete");
    
    // Verify task exists
    auto retrieved_task = agenda->getTaskById(task.id);
    EXPECT_FALSE(retrieved_task.id.empty());
    
    // Delete task
    EXPECT_TRUE(agenda->deleteTask(task.id));
    
    // Verify task is gone
    auto deleted_task = agenda->getTaskById(task.id);
    EXPECT_TRUE(deleted_task.id.empty());
}

TEST_F(AgentAgendaTest, CurrentTaskManagement) {
    auto task1 = agenda->createTask("First task");
    auto task2 = agenda->createTask("Second task");
    
    // Second task should be current
    auto current_task = agenda->getCurrentTask();
    EXPECT_EQ(current_task.id, task2.id);
    
    // Set first task as current
    EXPECT_TRUE(agenda->setCurrentTask(task1.id));
    
    current_task = agenda->getCurrentTask();
    EXPECT_EQ(current_task.id, task1.id);
    
    // Verify second task is no longer current
    auto task2_updated = agenda->getTaskById(task2.id);
    EXPECT_FALSE(task2_updated.current);
}

TEST_F(AgentAgendaTest, SearchTasks) {
    agenda->createTask("Learn Python programming");
    agenda->createTask("Build C++ application");
    agenda->createTask("Study machine learning");
    
    auto programming_tasks = agenda->searchTasks("programming");
    EXPECT_GE(programming_tasks.size(), 1);
    
    bool found_python = false;
    for (const auto& task : programming_tasks) {
        if (task.goal.find("Python") != std::string::npos) {
            found_python = true;
            break;
        }
    }
    EXPECT_TRUE(found_python);
}

TEST_F(AgentAgendaTest, UpdatePlan) {
    auto task = agenda->createTask("Task with plan to update");
    std::string new_plan = "Updated comprehensive plan";
    
    EXPECT_TRUE(agenda->updatePlan(task.id, new_plan));
    
    auto updated_task = agenda->getTaskById(task.id);
    EXPECT_EQ(updated_task.plan, new_plan);
}

TEST_F(AgentAgendaTest, StepManagement) {
    auto task = agenda->createTask("Task for step management");
    
    // Add a step
    EXPECT_TRUE(agenda->addStep(task.id, "New custom step"));
    
    auto updated_task = agenda->getTaskById(task.id);
    
    // Find the added step
    bool found_step = false;
    for (const auto& step : updated_task.steps) {
        if (step.content == "New custom step") {
            found_step = true;
            EXPECT_FALSE(step.completed);
            break;
        }
    }
    EXPECT_TRUE(found_step);
    
    // Finish the step
    EXPECT_TRUE(agenda->finishStep(task.id, "New custom step"));
    
    updated_task = agenda->getTaskById(task.id);
    for (const auto& step : updated_task.steps) {
        if (step.content == "New custom step") {
            EXPECT_TRUE(step.completed);
            break;
        }
    }
}

TEST_F(AgentAgendaTest, CancelStep) {
    auto task = agenda->createTask("Task for step cancellation");
    
    // Add a step
    agenda->addStep(task.id, "Step to be cancelled");
    
    auto updated_task = agenda->getTaskById(task.id);
    size_t steps_before = updated_task.steps.size();
    
    // Cancel the step
    EXPECT_TRUE(agenda->cancelStep(task.id, "Step to be cancelled"));
    
    updated_task = agenda->getTaskById(task.id);
    EXPECT_EQ(updated_task.steps.size(), steps_before - 1);
    
    // Verify step is gone
    bool found_step = false;
    for (const auto& step : updated_task.steps) {
        if (step.content == "Step to be cancelled") {
            found_step = true;
            break;
        }
    }
    EXPECT_FALSE(found_step);
}

TEST_F(AgentAgendaTest, UpdateStep) {
    auto task = agenda->createTask("Task for step updating");
    
    // Add a step
    agenda->addStep(task.id, "Original step");
    
    // Update the step
    AgendaTaskStep new_step("Updated step content", true);
    EXPECT_TRUE(agenda->updateStep(task.id, "Original step", new_step));
    
    auto updated_task = agenda->getTaskById(task.id);
    
    // Verify step was updated
    bool found_updated = false;
    for (const auto& step : updated_task.steps) {
        if (step.content == "Updated step content") {
            found_updated = true;
            EXPECT_TRUE(step.completed);
            break;
        }
    }
    EXPECT_TRUE(found_updated);
    
    // Verify old step is gone
    bool found_old = false;
    for (const auto& step : updated_task.steps) {
        if (step.content == "Original step") {
            found_old = true;
            break;
        }
    }
    EXPECT_FALSE(found_old);
}

TEST_F(AgentAgendaTest, GetLastCreatedTask) {
    agenda->createTask("First task");
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Ensure different timestamps
    auto second_task = agenda->createTask("Second task");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    agenda->createTask("Third task");
    
    auto last_created = agenda->getLastCreatedTask();
    EXPECT_EQ(last_created.goal, "Third task");
}

TEST_F(AgentAgendaTest, GetLastUpdatedTask) {
    auto task1 = agenda->createTask("First task");
    auto task2 = agenda->createTask("Second task");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    // Update first task
    agenda->updatePlan(task1.id, "Updated plan");
    
    auto last_updated = agenda->getLastUpdatedTask();
    EXPECT_EQ(last_updated.id, task1.id);
}

TEST_F(AgentAgendaTest, GetTaskAsFormattedString) {
    auto task = agenda->createTask("Sample task for formatting");
    
    auto formatted = agenda->getTaskAsFormattedString(task, true, true, true, true);
    
    EXPECT_TRUE(formatted.find("Sample task for formatting") != std::string::npos);
    EXPECT_TRUE(formatted.find("ID:") != std::string::npos);
    EXPECT_TRUE(formatted.find("Status:") != std::string::npos);
    EXPECT_TRUE(formatted.find("Plan:") != std::string::npos);
    EXPECT_TRUE(formatted.find("Steps:") != std::string::npos);
    EXPECT_TRUE(formatted.find("CURRENT") != std::string::npos);
}

TEST_F(AgentAgendaTest, ListTasksAsFormattedString) {
    agenda->createTask("Task 1");
    agenda->createTask("Task 2");
    
    auto formatted = agenda->listTasksAsFormattedString();
    
    EXPECT_TRUE(formatted.find("Current Tasks (2)") != std::string::npos);
    EXPECT_TRUE(formatted.find("Task 1") != std::string::npos);
    EXPECT_TRUE(formatted.find("Task 2") != std::string::npos);
}

TEST_F(AgentAgendaTest, EmptyTaskList) {
    auto tasks = agenda->listTasks(AgendaTaskStatus::IN_PROGRESS);
    EXPECT_TRUE(tasks.empty());
    
    auto current_task = agenda->getCurrentTask();
    EXPECT_TRUE(current_task.id.empty());
    
    auto formatted = agenda->listTasksAsFormattedString();
    EXPECT_TRUE(formatted.find("No tasks in progress") != std::string::npos);
}

TEST_F(AgentAgendaTest, NonExistentOperations) {
    // Operations on non-existent tasks should return false
    EXPECT_FALSE(agenda->deleteTask("non-existent"));
    EXPECT_FALSE(agenda->finishTask("non-existent"));
    EXPECT_FALSE(agenda->cancelTask("non-existent"));
    EXPECT_FALSE(agenda->setCurrentTask("non-existent"));
    EXPECT_FALSE(agenda->updatePlan("non-existent", "new plan"));
    EXPECT_FALSE(agenda->addStep("non-existent", "new step"));
    EXPECT_FALSE(agenda->finishStep("non-existent", "step"));
    EXPECT_FALSE(agenda->cancelStep("non-existent", "step"));
    
    AgendaTaskStep new_step("content", false);
    EXPECT_FALSE(agenda->updateStep("non-existent", "old", new_step));
}