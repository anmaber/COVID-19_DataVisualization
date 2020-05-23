import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    id: it
    width: 800
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: map
        objectName: "map"

        anchors.fill: parent
        plugin: mapPlugin
        zoomLevel: 0

        function addCircle(col, name, rad, lat, lon)
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
