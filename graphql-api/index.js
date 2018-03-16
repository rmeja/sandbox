const fs = require('fs');
const path = require('path');
const express = require('express');
const graphqlHTTP = require('express-graphql');
const { makeExecutableSchema } = require('graphql-tools');

const schemaFile = path.resolve('schema.graphql');
const typeDefs = fs.readFileSync(schemaFile, 'utf8');

const tweets = [
    { id: 1, body: 'Lorem Ipsum', date: new Date(), author_id: 10 },
    { id: 2, body: 'Sic dolor amet', date: new Date(), author_id: 11 }
];
const authors = [
    { id: 10, username: 'johndoe', first_name: 'John', last_name: 'Doe', avatar_url: 'acme.com/avatars/10' },
    { id: 11, username: 'janedoe', first_name: 'Jane', last_name: 'Doe', avatar_url: 'acme.com/avatars/11' },
];
const stats = [
    { tweet_id: 1, views: 123, likes: 4, retweets: 1, responses: 0 },
    { tweet_id: 2, views: 567, likes: 45, retweets: 63, responses: 6 }
];

const resolvers = {
    Query: {
        Tweets: () => tweets,
        Tweet: (_, { id }) => tweets.find(tweet => tweet.id == id),
    },
    Tweet: {
        Author: (tweet) => authors.find(author => author.id == tweet.author_id),
        Stats: (tweet) => stats.find(stat => stat.tweet_id == tweet.id),
    },
    User: {
        full_name: (author) => `${author.first_name} ${author.last_name}`
    },
};

const schema = makeExecutableSchema({ typeDefs, resolvers });
const app = express();
app.use('/graphql', graphqlHTTP({
    schema,
    graphiql: true
}));
app.listen(4000);

console.log('Running a GraphQL API server at http://localhost:4000/graphql');


