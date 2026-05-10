//! Web server entry point.
//! This server implements a basic HTTP/1.1 thread-pool based request handler.

use hello::ThreadPool;
use std::{
    fs,
    io::{BufReader, prelude::*},
    net::{TcpListener, TcpStream},
    thread,
    time::Duration,
};

fn main() {
    // Bind to the local interface. In production, graceful error handling
    // should be implemented instead of unwrap.
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    // Initialize a fixed-size thread pool to prevent unbounded thread creation
    // and mitigate potential DoS attacks.
    let pool = ThreadPool::new(4);

    // Limit to 2 incoming connections to demonstrate graceful shutdown.
    // In a production environment, this would be a continuous loop managed
    // by system signals (e.g., SIGTERM).
    for stream in listener.incoming().take(2) {
        let stream = stream.unwrap();

        pool.execute(|| {
            handle_connection(stream);
        });
    }

    println!("Shutting down.");
}

/// Parses the incoming HTTP request and serves the appropriate static asset.
/// 
/// Note: Currently only supports basic GET requests.
fn handle_connection(mut stream: TcpStream) {
    let buf_reader = BufReader::new(&stream);

    // Read the first line of the HTTP request to determine the route.
    let request_line = buf_reader.lines().next().unwrap().unwrap();

    // Route the request based on the path.
    let (status_line, filename) = match &request_line[..] {
        "GET / HTTP/1.1" => ("HTTP/1.1 200 OK", "hello.html"),
        "GET /sleep HTTP/1.1" => {
            // Simulate a slow IO operation to test thread pool concurrency.
            thread::sleep(Duration::from_secs(5));
            ("HTTP/1.1 200 OK", "hello.html")
        }
        // Fallback for unsupported routes.
        _ => ("HTTP/1.1 404 NOT FOUND", "404.html"),
    };

    // Load the requested HTML file.
    // In production, asset contents should ideally be cached in memory 
    // rather than performing disk I/O on every request.
    let contents = fs::read_to_string(filename).unwrap();
    let length = contents.len();

    // Construct the standard HTTP/1.1 response including headers and body.
    let response = format!(
        "{status_line}\r\nContent-Length: {length}\r\n\r\n{contents}"
    );

    stream.write_all(response.as_bytes()).unwrap();
}

