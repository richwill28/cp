use std::io;
use std::str;

pub struct Reader<R> {
    buffer: Vec<String>,
    inner: R,
}

impl<R: io::BufRead> Reader<R> {
    pub fn new(inner: R) -> Self {
        Self {
            buffer: Vec::new(),
            inner,
        }
    }

    pub fn read<T: str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parsing token");
            }

            let mut input = String::new();
            self.inner
                .read_line(&mut input)
                .expect("Failed reading input");
            self.buffer = input.split_whitespace().map(String::from).collect();
        }
    }
}
