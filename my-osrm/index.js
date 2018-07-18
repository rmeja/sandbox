const util = require('util');
const Promise = require('bluebird');
const OSRM = require('osrm');

// wget http://download.geofabrik.de/europe/france/lorraine-latest.osm.pbf
// node_modules/osrm/lib/binding/osrm-extract lorraine-latest.osm.pbf -p node_modules/osrm/profiles/car.lua
// node_modules/osrm/lib/binding/osrm-contract lorraine-latest.osrm
const osrm = Promise.promisifyAll(new OSRM('lorraine-latest.osrm'));

// osrm.routeAsync({
//   coordinates: [
//     [6.188322901725769, 48.70818873021267],
//     [6.1622974, 48.7061891]
//   ],
//   steps: true
// }).then(response => {
//   console.log(util.inspect(response, { colors: true, depth: null }));
// });

osrm.tripAsync({
  coordinates: [
    [6.188322901725769, 48.70818873021267], // rue colonel driant
    [6.2202132, 48.6784264], // rue Mozart
    [6.1622974, 48.7061891], // avenue du général patton
    [6.17465970440687, 48.6542605], // rue arthur rimbaud
    [6.1808076, 48.6778487] // boulevard georges clemenceau
  ]
}).then(response => {
  console.log(util.inspect(response, { colors: true, depth: null }));
});
