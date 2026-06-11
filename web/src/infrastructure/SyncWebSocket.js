export class SyncWebSocket {
    constructor() {
        this.ws = null;
        this.wsErrorLogged = false;
        this.listeners = {
            beat: [],
            tx: [],
            rx: []
        };
    }

    on(event, callback) {
        if (this.listeners[event]) {
            this.listeners[event].push(callback);
        }
    }

    emit(event, data) {
        if (this.listeners[event]) {
            this.listeners[event].forEach(cb => {
                try { cb(data); } catch (e) { console.error('WS event callback error:', e); }
            });
        }
    }

    connect() {
        this.ws = new WebSocket("ws://127.0.0.1:8002");
        
        this.ws.onerror = (err) => {
            if (!this.wsErrorLogged) {
                console.warn("Ableton Link Bridge no detectado (ws://127.0.0.1:8002). El sintetizador funcionará con reloj interno.");
                this.wsErrorLogged = true;
            }
        };

        this.ws.onmessage = (event) => {
            try {
                this.wsErrorLogged = false;
                const data = JSON.parse(event.data);
                if (data.type === "beat") {
                    this.emit('beat', data);
                } else if (data.type === "tx") {
                    this.emit('tx', data);
                } else if (data.type === "rx") {
                    this.emit('rx', data);
                }
            } catch (e) {
                // Ignore parsing errors
            }
        };

        this.ws.onclose = () => {
            setTimeout(() => this.connect(), 3000);
        };
    }
}
