'use strict';

const readline = require('readline');
const fs = require('fs');

module.exports = function (path) {
  return new Promise(function (resolve, reject) {
    const fileStream = fs.createReadStream(path, 'utf8');
    fileStream.on('error', (error) => {
      reject(error);
    })
    const rl = readline.createInterface({
      input: fileStream
    });
    rl.on('line', (line) => {
      resolve(line);
      rl.close();
    });
    rl.on('error', (error) => {
      reject(error);
    })
  });
};
