import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin

        MapCircle {
            center {
                latitude: -27.5
                longitude: 153.0
            }
            radius: 50000.0
            color: 'green'
            border.width: 3
            opacity : 1
        }
        center: QtPositioning.coordinate(-27.5, 153.0)
        zoomLevel: 0

    }
}
