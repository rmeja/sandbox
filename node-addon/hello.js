const addon = require('./build/Release/addon');

// Hello World synchronous
console.log(addon.hello());

// Hello World asynchronous
addon.helloAsync((result) => {
  console.log(result)
});