import React, {Component} from 'react';
import 'ol/ol.css';
import Map from 'ol/map';
import View from 'ol/view';
import Tile from 'ol/layer/tile';
import OSM from 'ol/source/osm';

class MapComponent extends Component {
    componentDidMount() {
        this.map = new Map({
            view: new View({
                center: [0, 0],
                zoom: 4
            }),
            layers: [
                new Tile({
                    source: new OSM()
                })
            ],
            target: 'map'
        });
    }
    render() {
        return (<div id="map"></div>);
    }
}

export default MapComponent;