import express from 'express';
import path from 'path';
import { fileURLToPath } from 'url';
import { GitHubBountyFetcher } from './github-bounties.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const PORT = process.env.PORT || 3000;

// Serve static files
app.use(express.static(__dirname));

// Add CORS headers
app.use((req, res, next) => {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
    next();
});

// Create bounties endpoint that fetches real data
app.get('/bounties.json', async (req, res) => {
    try {
        console.log('Fetching bounties...');
        const fetcher = new GitHubBountyFetcher();
        const bounties = await fetcher.fetchBountyIssues();
        console.log('Bounties response:', bounties);
        res.json(bounties);
    } catch (error) {
        console.error('Detailed error:', error);
        res.status(500).json({ error: 'Failed to fetch bounties', details: error.message });
    }
});

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
}); 