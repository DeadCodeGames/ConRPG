const { Octokit } = require('@octokit/rest');

// Initialize Octokit with GitHub token
const octokit = new Octokit({ auth: process.env.ISSUES_TOKEN });

async function updateIssueDates(eventPayload) {
  try {
    const { action, issue } = eventPayload;

    if (action === 'opened') {
      // Update started_at field when issue is opened
      await octokit.issues.update({
        owner: issue.repository.owner.login,
        repo: issue.repository.name,
        issue_number: issue.number,
        started_at: new Date().toISOString(),
      });
    } else if (action === 'closed') {
      // Update finished_at field when issue is closed
      await octokit.issues.update({
        owner: issue.repository.owner.login,
        repo: issue.repository.name,
        issue_number: issue.number,
        finished_at: new Date().toISOString(),
      });
    }
  } catch (error) {
    console.error('Error updating issue dates:', error.message);
  }
}

// Parse GitHub event payload passed as command line argument
const eventPayload = JSON.parse(process.argv[2]);

// Call the function to update issue dates
updateIssueDates(eventPayload);
