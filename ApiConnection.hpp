class ApiConnection {
public:
    void send(String data) {
        Serial.write(data + "\n");
    }

    String receive() {
        Serial.readStringUntil("\n");
    }
}