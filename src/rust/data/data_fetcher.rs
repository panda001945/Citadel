use reqwest;
use serde_json::Value;

pub struct DataFetcher {
    api_key: String,
    base_url: String,
}

impl DataFetcher {
    pub fn new(api_key: String, base_url: String) -> Self {
        DataFetcher { api_key, base_url }
    }

    pub async fn fetch_data(&self, endpoint: &str) -> Result<Value, reqwest::Error> {
        let client = reqwest::Client::new();
        let url = format!("{}/{}", self.base_url, endpoint);
        let response = client
            .get(&url)
            .header("X-API-KEY", &self.api_key)
            .send()
            .await?
            .json::<Value>()
            .await?;
        Ok(response)
    }
}