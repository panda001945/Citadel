#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "data/data_fetcher.hpp"
#include "models/strategy1.hpp"
#include "utils/config_loader.hpp"
#include "utils/database_logger.hpp"
#include "execution/trade_executor.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QWidget *centralWidget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;
        textEdit = new QTextEdit;
        textEdit->setReadOnly(true);
        
        // Trading controls
        symbolInput = new QLineEdit;
        quantityInput = new QLineEdit;
        buyButton = new QPushButton("Buy");
        sellButton = new QPushButton("Sell");

        layout->addWidget(textEdit);
        layout->addWidget(new QLabel("Symbol:"));
        layout->addWidget(symbolInput);
        layout->addWidget(new QLabel("Quantity:"));
        layout->addWidget(quantityInput);
        layout->addWidget(buyButton);
        layout->addWidget(sellButton);

        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
        
        setWindowTitle("Citadel Trading System");

        // Setup trading components
        dbLogger = new DatabaseLogger("logs/citadel.db");
        configLoader = new ConfigLoader("config/trading_config.json");
        strategy = new TradingStrategy();
        executor = new TradeExecutor();

        // Connect signals
        connect(buyButton, &QPushButton::clicked, this, &MainWindow::onBuyClicked);
        connect(sellButton, &QPushButton::clicked, this, &MainWindow::onSellClicked);

        dbLogger->log("INFO", "Starting the Citadel trading system...");
        textEdit->append("Starting the Citadel trading system...");
    }

private slots:
    void onBuyClicked() {
        executeTrade("BUY");
    }

    void onSellClicked() {
        executeTrade("SELL");
    }

private:
    void executeTrade(const std::string& action) {
        QString symbol = symbolInput->text();
        double quantity = quantityInput->text().toDouble();
        if (symbol.isEmpty() || quantity <= 0) {
            textEdit->append("Invalid input for trade action.");
            return;
        }
        try {
            double price = strategy->get_current_price(symbol.toStdString());
            executor->execute_trade(action, symbol.toStdString(), quantity, price);
            textEdit->append(QString::fromStdString(action + " order for " + symbol.toStdString() + " executed."));
            dbLogger->log("INFO", action + " order for " + symbol.toStdString() + " executed.");
        } catch (const std::exception& e) {
            textEdit->append(QString::fromStdString(std::string("Error executing trade: ") + e.what()));
            dbLogger->log("ERROR", "Error executing trade: " + std::string(e.what()));
        }
    }

    QTextEdit *textEdit;
    QLineEdit *symbolInput, *quantityInput;
    QPushButton *buyButton, *sellButton;
    DatabaseLogger *dbLogger;
    ConfigLoader *configLoader;
    TradingStrategy *strategy;
    TradeExecutor *executor;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"