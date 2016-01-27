import QtQuick 2.5
import QtQuick.Window 2.2

Window {
  visible: true

  function send(msg) {
      receiver.receiveFromQml(msg)
  }

  Connections {
    target: receiver
    onSendToQml: {
        console.log("Received in QML from C++: " + count)
    }
  }
  TextInput {
      text: "Enter command here"
      onAccepted: {
          send(text)
      }
  }
  Motor {
  }
}
