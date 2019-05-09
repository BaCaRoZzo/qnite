import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.3

import Qnite 1.0


ApplicationWindow {
    width: 1600; height: 900
    visible: true

    readonly property int dataSourcePonishingSet: 100
    readonly property int autoupdateInterval: 100
    readonly property int dataSourceGenerationInterval: 2000
    readonly property int shownInterval: 10000 // 10 seconds
    readonly property int valuesAtScreen: (shownInterval / dataSourceGenerationInterval) + 1 //(off-screen reference point)
    readonly property real currentTime: new Date().getTime()


    ColumnLayout {
        anchors.fill: parent

        RowLayout
        {
            CheckBox {
                id: _drawContinuously
                text: "Draw continuosly"
                checked: true
            }
        }

        Figure {
            id: figure
            axes.yBounds: [-0.2, 0.65]
            axes.xBounds: [currentTime - shownInterval, currentTime]

            axes.axisX: TimelineAxis
            {
                ticker.numSteps: 10
                formattingString: "hh:mm:ss"
            }

            Grid { }
            Strip {
                id: line
                xValues: [0.0]
                yValues: [0.3]

                pen.stroke: "#0000AA"

                drawSymbols: false
                continuousDrawning: _drawContinuously.checked
            }

            Strip {
                id: line2
                xValues: [0.0]
                yValues: [0.2]

                pen.stroke: "#AA0000"

                drawSymbols: false
                continuousDrawning: _drawContinuously.checked
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Timer
    {
        running: _drawContinuously.checked
        interval: autoupdateInterval
        repeat: true

        onTriggered: {
            figure.axes.xBounds[0] = figure.axes.xBounds[0] + autoupdateInterval
            figure.axes.xBounds[1] = figure.axes.xBounds[1] + autoupdateInterval
        }
    }

    Timer
    {
        running: true
        interval: dataSourceGenerationInterval
        repeat: true
        triggeredOnStart: true

        onTriggered: {
            var xValue = new Date().getTime()

            line.xValues.push(xValue)
            line.yValues.push(Math.random() * 0.5)
            line2.xValues.push(xValue)
            line2.yValues.push(Math.random() * 0.2)
            if (line.xValues.length >= dataSourcePonishingSet) {
                line.xValues.splice(0, dataSourcePonishingSet - valuesAtScreen)
                line.yValues.splice(0, dataSourcePonishingSet - valuesAtScreen)
                line2.xValues.splice(0, dataSourcePonishingSet - valuesAtScreen)
                line2.yValues.splice(0, dataSourcePonishingSet - valuesAtScreen)
            }
            if (!_drawContinuously.checked) {
                figure.axes.xBounds[0] = xValue - shownInterval
                figure.axes.xBounds[1] = xValue
            }
        }
    }
}
