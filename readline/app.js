'use strict';
const firstline = require('./firstline');

firstline('test.txt').then((result) => {
  console.log(result)
}).catch((error) => {
  console.log(error)
})
