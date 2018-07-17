const OSRM = require('osrm');

const osrm = new OSRM('lorraine-latest.osrm');

osrm.route({
  coordinates: [[6.188322901725769, 48.70818873021267], [6.1622974, 48.7061891]],
  steps: true
}, function (err, response) {
  if (err) throw err;
  response.routes.map(route => {
    route.legs.map(leg => {
      leg.steps.map(step => {
        console.log('step :', step);
      });
    });
  });
});
