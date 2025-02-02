use std::io::{self,Write};
fn main() {
    print!("input numbers:");
    io::stdout().flush().unwrap();
    let mut input=String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Wrong!");
    let numbers:Vec<i32>=input
        .split_whitespace()
        .map(|s| s.parse().expect("Wrong!"))
        .collect();
    let sum:i32=numbers.iter().sum();
    println!("sum={}",sum);
}
