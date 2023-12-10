use std::collections::HashMap;

#[macro_use]
extern crate lazy_static;

lazy_static! {
    static ref HASHMAP: HashMap<u32, &'static str> = {
        let m = HashMap::new();
        m
    };
}

#[no_mangle]
pub extern fn worldserver_rs_handle_spell(spell_id: u32) -> bool {
    if let Some(&value) = HASHMAP.get(&spell_id) {
        println!("Hello world - {}", value);
        return true;
    } else {
        println!("No spell found!");
        return false;
    }
}

