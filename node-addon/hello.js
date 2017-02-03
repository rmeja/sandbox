// hello.js
const addon = require('./build/Release/addon');

console.log(addon.hello()); // 'world'
addon.helloAsync((result) => {
  console.log(result)
})