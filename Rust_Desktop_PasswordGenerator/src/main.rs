use std::{env, io::Read, vec};
use rand::Rng;

fn main() {
    let args: Vec<String> = env::args().collect();
    let symbols: Vec<Vec<u8>> = vec![(b'0'..=b'9').collect(), (b'a'..=b'z').collect(), (b'A'..=b'Z').collect(), vec![b'@', b'!', b'#',b'$',b'%',b'^',b'&',b'*',b'(',b')',b'_', b',' , b'.' ,b'/', b'\'', b'\"', b';', b':', b'`', b'-', b'+', b'=']];
    let use_specials: i8;
    match args.get(1){
        Some(_arg) => if args[1] == "Yes".to_string() {use_specials=1} else {use_specials=0},
        None => use_specials = 0,
    }
    for _i in 0..100{
        const MIN_LEN: u8 = 6;
        const MAX_LEN: u8 = 18;

        let random_len = rand::thread_rng().gen_range(MIN_LEN..=MAX_LEN);
        let mut vec_pass: Vec<u8> = vec![];
        for _j in 0..random_len{
            let random_row = rand::thread_rng().gen_range(0..((symbols.len() as i8)+(use_specials-1))) as usize;
            let random_col = rand::thread_rng().gen_range(0..symbols[random_row].len());
            vec_pass.push(symbols[random_row][random_col])
        }
        
        print!("{}\n", String::from_utf8(vec_pass).expect("Couldn't cast vec"));
    }
    /* read char to prevent program from closing instantly
        let mut char_buff = [0; 1];
        std::io::stdin().read_exact(&mut char_buff).expect("Couldn't read char");
    */
}

