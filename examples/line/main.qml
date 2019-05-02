import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

import Qnite 1.0


ApplicationWindow {
    width: 1600; height: 900
    visible: true

    ColumnLayout {
        anchors.fill: parent

        RowLayout
        {
            CheckBox {
                id: _drawSymbols
                text: "Draw Symbols"
            }

            CheckBox {
                id: _drawStepped
                text: "Draw Stepped line"
            }

            CheckBox {
                id: _drawContinuously
                text: "Draw continuosly"
                checked: true
            }
        }

        Figure {
            id: figure
            axes.yBounds: [-0.2, 0.65]
            axes.xBounds: [51666039, 51706039]

            axes.axisX: TimelineAxis
            {
                ticker.numSteps: 10
                formattingString: "hh:mm:ss"
            }

            Grid { }
            Strip {
                id: line
                xValues: [0.0001, 0.00013, 0.0003, 0.0004, 0.0005, 0.00055]
                yValues: [0.2,        0.3,    0.6,    0.3,    0.4,     0.2]

                pen.stroke: "#0000AA"

                drawSymbols: _drawSymbols.checked
                drawStepped: _drawStepped.checked
                continuousDrawning: _drawContinuously.checked
            }

            Strip {
                id: line2
                xValues: [0.0001, 0.00013, 0.0003, 0.0004, 0.0005, 0.00055]
                yValues: [0.2,        0.3,    0.6,    0.3,    0.4,     0.2]

                pen.stroke: "#AA0000"

                drawSymbols: _drawSymbols.checked
                drawStepped: _drawStepped.checked
                continuousDrawning: _drawContinuously.checked
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Timer
    {
        running: _drawContinuously.checked
        interval: 100
        repeat: true

        onTriggered: {
            figure.axes.xBounds[0] = figure.axes.xBounds[0] + 100
            figure.axes.xBounds[1] = figure.axes.xBounds[1] + 100
        }
    }

    Timer
    {
        running: true
        interval: 2000
        repeat: true

        onTriggered: {

            line.xValues.push(figure.axes.xBounds[1])
            line.yValues.push(Math.random(0.2))
            line2.xValues.push(figure.axes.xBounds[1])
            line2.yValues.push(Math.random(0.2))
            if (!_drawContinuously.checked) {

            }
        }
    }
}
