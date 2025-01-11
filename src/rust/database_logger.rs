use sqlx::{SqlitePool, sqlite::SqlitePoolOptions};
use log::{Level, Log, Metadata, Record};

pub struct DatabaseLogger {
    pool: SqlitePool,
}

impl DatabaseLogger {
    pub async fn new(db_path: &str) -> Result<Self, sqlx::Error> {
        let pool = SqlitePoolOptions::new()
            .max_connections(5)
            .connect(&format!("sqlite://{}", db_path))
            .await?;

        sqlx::query(
            "CREATE TABLE IF NOT EXISTS logs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                level TEXT,
                message TEXT,
                timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
            )"
        ).execute(&pool).await?;

        Ok(DatabaseLogger { pool })
    }

    pub async fn log(&self, level: &str, message: &str) -> Result<(), sqlx::Error> {
        sqlx::query("INSERT INTO logs (level, message) VALUES (?, ?)")
            .bind(level)
            .bind(message)
            .execute(&self.pool).await?;
        Ok(())
    }
}

impl Log for DatabaseLogger {
    fn enabled(&self, _metadata: &Metadata) -> bool {
        true
    }

    fn log(&self, record: &Record) {
        let rt = tokio::runtime::Runtime::new().unwrap();
        rt.block_on(async {
            if self.enabled(record.metadata()) {
                self.log(&record.level().to_string(), &record.args().to_string()).await.unwrap();
            }
        });
    }

    fn flush(&self) {}
}