import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    id: it
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
        objectName: "map"

        anchors.fill: parent
        plugin: mapPlugin

        //        MapCircle {
        //            objectName: "circ"
        //            center {
        //                latitude: -27.5
        //                longitude: 153.0
        //            }
        //            radius: 50000.0
        //            color: 'green'
        //            border.width: 0
        //            opacity : 1
        //        }
        center: QtPositioning.coordinate(-27.5, 153.0)
        zoomLevel: 0

        property MapCircle circle
        Component.onCompleted:
        {
            addCircle('green','circ',50000.0,-27.5,153.0)
//            circle = Qt.createQmlObject('import QtLocation 5.3; MapCircle {}',it)
//            circle.center = QtPositioning.coordinate(-27.5,153.0)
//            circle.radius = 50000.0
//            circle.color = 'green'
//            circle.objectName = "circ"
//            map.addMapItem(circle)
        }

        function addCircle(col,name, rad, lat, lon)
        {
            var circl = Qt.createQmlObject('import QtLocation 5.3; MapCircle {}',it)
            circl.objectName = name
            circl.center = QtPositioning.coordinate(lat,lon)
            circl.color = col
            circl.radius = rad
            map.addMapItem(circl)
        }
    }


}
