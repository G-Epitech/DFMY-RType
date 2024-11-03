import { useEffect, useState } from 'react';

const useWebSocket = (url: string) => {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    const [messages, setMessages] = useState<any[]>([]);
    const [ws, setWs] = useState<WebSocket | null>(null);

    useEffect(() => {
        const socket = new WebSocket(url);
        setWs(socket);

        socket.onmessage = (event) => {
            setMessages((prevMessages) => [...prevMessages, JSON.parse(event.data)]);
        };

        return () => {
            socket.close();
        };
    }, [url]);

    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    const sendMessage = (message: object) => {
        if (ws) {
            ws.send(JSON.stringify(message));
        }
    };

    const clearMessages = () => {
        setMessages([]);
    }

    return { messages, sendMessage, clearMessages };
};

export default useWebSocket;
