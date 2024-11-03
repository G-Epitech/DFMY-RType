import type {Metadata} from "next";
import {NextUIProvider} from '@nextui-org/react';
import localFont from "next/font/local";
import "./globals.css";

const geistSans = localFont({
    src: "./fonts/GeistVF.woff",
    variable: "--font-geist-sans",
    weight: "100 900",
});
const geistMono = localFont({
    src: "./fonts/GeistMonoVF.woff",
    variable: "--font-geist-mono",
    weight: "100 900",
});

export const metadata: Metadata = {
    title: "📟 RType Monitor",
    description: "Monitor for RType",
};

export default function RootLayout({
                                       children,
                                   }: Readonly<{
    children: React.ReactNode;
}>) {
    return (
        <html lang="en">
        <body
            className={`${geistSans.variable} ${geistMono.variable} antialiased dark text-foreground bg-background`}
        >
        <NextUIProvider>
            {children}
        </NextUIProvider>
        </body>
        </html>
    );
}
