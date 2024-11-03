"use client";

import {useEffect, useState} from "react";
import {Button} from "@nextui-org/button";
import {Input} from "@nextui-org/input";
import {Card, CardBody, CardHeader} from "@nextui-org/card";
import useWebSocket from "./websocket";

type Player = {
    id: number;
    name: string;
    inGame: boolean;
};

type Node = {
    id: number,
    name: string;
    ping: number;
    maxRooms: number;
    currentRooms: number;
    status: "free" | "partial" | "unavailable";
};

type Room = {
    id: number,
    name: string;
    players: number;
    maxPlayers: number;
};

export default function MonitorPage() {
    const {messages, sendMessage, clearMessages} = useWebSocket('ws://localhost:8060');
    const [token, setToken] = useState('');
    const [connected, setConnected] = useState(false);
    const [players, setPlayers] = useState<Player[]>([]);
    const [nodes, setNodes] = useState<Node[]>([]);
    const [rooms, setRooms] = useState<Room[]>([]);

    const sendToken = () => {
        sendMessage({
            type: 'auth',
            token: token,
        });
    };

    const handleKickPlayer = (playerId: number) => {
        sendMessage({
            type: 'kick',
            token: token,
            id: playerId,
        });
    };

    useEffect(() => {
        if (!messages.length) return;

        for (const message of messages) {
            switch (message.type) {
                case 'auth':
                    if (message.status === "ok") setConnected(true);
                    break;
                case 'players':
                    setPlayers(message.players);
                    break;
                case 'nodes':
                    setNodes(message.nodes);
                    break;
                case 'rooms':
                    setRooms(message.rooms);
                    break;
            }
        }
        clearMessages();
    }, [messages, clearMessages]);

    if (!connected) {
        return (
            <div className="h-screen flex items-center justify-center">
                <div className="flex gap-2 items-end">
                    <Input
                        type="password"
                        label="Token"
                        placeholder="Enter the master token"
                        labelPlacement="outside"
                        value={token}
                        onChange={(e) => setToken(e.target.value)}
                    />
                    <Button color="success" onClick={sendToken}>Connect</Button>
                </div>
            </div>
        );
    }

    return (
        <div className="container mx-auto p-4 space-y-4">
            <h1 className="text-2xl font-bold mb-4">Game Monitor 📟</h1>
            <div className="grid grid-cols-1 md:grid-cols-3 gap-4">
                <Card>
                    <CardHeader className="font-bold">Players</CardHeader>
                    <CardBody>
                        <ul className="space-y-2">
                            {players.map((player, index) => (
                                <li key={index} className="flex justify-between items-center">
                                    <span>{player.name}</span>
                                    <div className="flex items-center gap-2">
                                        <span
                                            className={`w-3 h-3 rounded-full ${player.inGame ? 'bg-success' : 'bg-danger'}`}></span>

                                        <Button
                                            size="sm"
                                            color={player.inGame ? 'danger' : 'default'}
                                            disabled={!player.inGame}
                                            onClick={() => handleKickPlayer(player.id)}
                                        >
                                            Kick
                                        </Button>

                                    </div>
                                </li>
                            ))}
                        </ul>
                    </CardBody>
                </Card>

                <Card>
                    <CardHeader className="font-bold">Nodes</CardHeader>
                    <CardBody>
                        <ul className="space-y-2">
                            {nodes.map((node, index) => (
                                <li key={index} className="space-y-1">
                                    <div className="flex justify-between">
                                        <span>{node.name}</span>
                                        <span className={`w-3 h-3 rounded-full ${
                                            node.status === 'free' ? 'bg-success' :
                                                node.status === 'partial' ? 'bg-warning' : 'bg-danger'
                                        }`}></span>
                                    </div>
                                    <div className="text-sm text-gray-600">
                                        Ping: {node.ping || 10}ms | Rooms: {node.currentRooms}/{node.maxRooms}
                                    </div>
                                </li>
                            ))}
                        </ul>
                    </CardBody>
                </Card>

                <Card>
                    <CardHeader className="font-bold">Rooms</CardHeader>
                    <CardBody>
                        <ul className="space-y-2">
                            {rooms.map((room, index) => (
                                <li key={index} className="flex justify-between items-center">
                                    <span>{room.name || "New room"}</span>
                                    <span className="text-sm text-gray-600">
                    Players: {room.players}/{room.maxPlayers}
                  </span>
                                </li>
                            ))}
                        </ul>
                    </CardBody>
                </Card>
            </div>
        </div>
    );
}
