"use client";

import {Button} from "@nextui-org/button";
import {Input} from "@nextui-org/input";

export default function Home() {
    return (
        <main className="h-screen flex items-center justify-center">
            <div className="flex gap-2 items-end">
                <Input type="password" variant="bordered" label="Token" placeholder="Enter the master token"
                       labelPlacement="outside"/>
                <Button type="submit" color="success" size="md">Connect</Button>
            </div>
        </main>
    );
}
