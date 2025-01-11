mod data;
mod utils;

use log::{info, error};
use utils::database_logger::DatabaseLogger;

// Placeholder for integrating Rust with C++ if needed. In reality, 
// might use FFI (Foreign Function Interface) to call Rust from C++ or vice versa.
pub fn init_rust_components() {
    let rt = tokio::runtime::Runtime::new().unwrap();
    rt.block_on(async {
        let db_logger = DatabaseLogger::new("logs/citadel.db").await.unwrap();
        log::set_boxed_logger(Box::new(db_logger)).unwrap();
        log::set_max_level(log::LevelFilter::Info);

        info!("Rust components initialized for Citadel system.");
    });
}