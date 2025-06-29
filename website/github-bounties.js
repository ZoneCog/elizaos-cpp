export class GitHubBountyFetcher {
    constructor() {
        this.owner = 'ai16z';
        this.repo = 'eliza';
        this.baseUrl = 'https://api.github.com';
    }

    // Helper method to ensure label text is readable
    getLabelTextColor(backgroundColor) {
        const hex = backgroundColor.replace('#', '');
        const r = parseInt(hex.substr(0, 2), 16);
        const g = parseInt(hex.substr(2, 2), 16);
        const b = parseInt(hex.substr(4, 2), 16);
        const luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255;
        return luminance > 0.5 ? '#000000' : '#FFFFFF';
    }

    async fetchBountyIssues() {
        try {
            const url = `${this.baseUrl}/repos/${this.owner}/${this.repo}/issues?labels=Bounty&state=open`;
            console.log('Fetching from URL:', url);

            const response = await fetch(url, {
                headers: {
                    'Accept': 'application/vnd.github.v3+json'
                },
                cache: 'no-store'
            });

            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }

            const issues = await response.json();
            return this.processIssues(issues);
        } catch (error) {
            console.error('Error fetching bounty issues:', error);
            return [];
        }
    }

    processIssues(issues) {
        return issues.map(issue => ({
            title: issue.title,
            number: issue.number,
            url: issue.html_url,
            created_at: new Date(issue.created_at),
            updated_at: new Date(issue.updated_at),
            labels: issue.labels.map(label => ({
                name: label.name,
                color: label.color,
                textColor: this.getLabelTextColor(`#${label.color}`)
            })),
            body: issue.body,
            user: {
                login: issue.user.login,
                avatar: issue.user.avatar_url,
                profile: issue.user.html_url
            }
        }));
    }
}

// Only run browser code if we're in a browser environment
if (typeof window !== 'undefined') {
    document.addEventListener('DOMContentLoaded', async () => {
        try {
            const container = document.getElementById('bounty-container');
            
            if (!container) {
                console.error('Bounty container not found');
                return;
            }

            container.innerHTML = '<p>Loading bounties...</p>';

            const bountyFetcher = new GitHubBountyFetcher();
            const issues = await bountyFetcher.fetchBountyIssues();
            
            if (issues.length === 0) {
                container.innerHTML = '<p class="no-bounties">No bounty issues found.</p>';
                return;
            }

            const issuesHTML = issues.map(issue => `
                <div class="bounty-issue">
                    <div class="bounty-header">
                        <h3>
                            <a href="${issue.url}" target="_blank" rel="noopener noreferrer">
                                ${issue.title}
                            </a>
                        </h3>
                        <div class="issue-meta">
                            <span class="issue-number">#${issue.number}</span>
                            <span class="issue-date">Created: ${issue.created_at.toLocaleDateString()}</span>
                        </div>
                    </div>
                    <div class="bounty-content">
                        <div class="issue-labels">
                            ${issue.labels.map(label => 
                                `<span class="label" style="background-color: #${label.color}; color: ${label.textColor}">
                                    ${label.name}
                                </span>`
                            ).join('')}
                        </div>
                        <div class="issue-user">
                            <img src="${issue.user.avatar}" alt="${issue.user.login}" class="user-avatar">
                            <a href="${issue.user.profile}" target="_blank" rel="noopener noreferrer">
                                ${issue.user.login}
                            </a>
                        </div>
                    </div>
                </div>
            `).join('');

            container.innerHTML = issuesHTML;
        } catch (error) {
            console.error('Error displaying bounties:', error);
            const container = document.getElementById('bounty-container');
            if (container) {
                container.innerHTML = `<p class="error-message">Error loading bounties: ${error.message}</p>`;
            }
        }
    });
} 