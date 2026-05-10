use std::fs;
use std::io::{BufRead, BufReader, Write};
use std::net::{TcpListener, TcpStream};

fn main() {
    // 1. 开门营业
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    // 2. 永远等待，来一个处理一个
    for stream in listener.incoming() {
        let stream = stream.unwrap();
        handle_connection(stream);
    }
}

fn handle_connection(mut stream: TcpStream) {
    // 3. 读请求（遇到空行停止）
    let buf_reader = BufReader::new(&stream);
    let request_line = buf_reader.lines().next().unwrap().unwrap();

    // 4. 判断请求，决定返回什么
    let (status_line, filename) = if request_line == "GET / HTTP/1.1" {
        ("HTTP/1.1 200 OK", "hello.html")
    } else {
        ("HTTP/1.1 404 NOT FOUND", "404.html")
    };

    // 5. 读文件，拼响应，发出去
    let contents = fs::read_to_string(filename).unwrap();
    let length = contents.len();
    let response = format!(
        "{status_line}\r\nContent-Length: {length}\r\n\r\n{contents}"
    );
    stream.write_all(response.as_bytes()).unwrap();
}