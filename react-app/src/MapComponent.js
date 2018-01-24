import React, { Component } from 'react';
import 'ol/ol.css';
import Map from 'ol/map';
import View from 'ol/view';
import Tile from 'ol/layer/tile';
import OSM from 'ol/source/osm';
import SourceVector from 'ol/source/vector';
import LayerVector from 'ol/layer/vector';
import Modify from 'ol/interaction/modify';
import Draw from 'ol/interaction/draw';
import Snap from 'ol/interaction/snap';

class MapComponent extends Component {
    constructor(props) {
        super(props);
        this.state = {value: 'Point'};
        this.handleChange = this.handleChange.bind(this);
    }
    componentDidMount() {
        this.initializeMap();
    }
    initializeMap() {
        this.raster = new Tile({
            source: new OSM()
        });
        this.source = new SourceVector();
        this.vector = new LayerVector({source: this.source})
        this.map = new Map({
            view: new View({
                center: [0, 0],
                zoom: 4
            }),
            layers: [this.raster, this.vector],
            target: 'map'
        });
        const modify = new Modify({source: this.source});
        this.draw = new Draw({
            source: this.source,
            type: 'Point'
          });
        this.snap = new Snap({source: this.source});
        this.map.addInteraction(modify);
        this.map.addInteraction(this.draw);
        this.map.addInteraction(this.snap);
    }
    handleChange(event) {
        this.setState({value: event.target.value});
        this.map.removeInteraction(this.draw);
        this.map.removeInteraction(this.snap);
        this.draw = new Draw({
            source: this.source,
            type: event.target.value
        });
        this.map.addInteraction(this.draw);
        this.snap = new Snap({source: this.source});
        this.map.addInteraction(this.snap);

    }
    render() {
        return (
            <div>
                <div id="map"></div>
                <form class="form-inline">
                <label>Geometry type &nbsp;</label>
                <select value={this.state.value} onChange={this.handleChange}>
                    <option value="Point">Point</option>
                    <option value="LineString">LineString</option>
                    <option value="Polygon">Polygon</option>
                    <option value="Circle">Circle</option>
                </select>
                </form>
            </div>
        )
    }
}

export default MapComponent;