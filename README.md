# Stock Analysis Tool

## Overview
This project is a **C program** that analyzes stocks using historical prices and financial metrics from Nifty 50 companies. It provides insights for investors, including:

- **Investment Advice** (long-term based on revenue, profit, PE, debt ratio, ROE)
- **Volatility Analysis** (short-term risk assessment)
- **Short-Term Trend Prediction** (predicts whether the stock is trending up, down, or stable)
- **Stock Comparison** (compare two stocks based on PE, debt ratio, and revenue growth)

The data is generated using a **Python script** that downloads stock data and creates a CSV.

## Included Files

- `stock_analysis.c` — Main C program for stock analysis
- `stock.py` — Python script to download Nifty 50 data and generate a CSV

## How to Use

### 1️⃣ Generate CSV using Python
Run the Python script to download Nifty 50 data and create a CSV:
python generate_csv.py
Note: You need Python installed with yfinance and pandas libraries:
Using the Program

When prompted, enter the stock ticker exactly as in the CSV (e.g., RELIANCE.NS, TCS.NS, HDFCBANK.NS).

Select one of the following options:

Option	Description
1	Investment Advice (long-term)
2	Volatility Analysis (short-term risk)
3	Short-Term Trend Prediction (up/down/stable)
4	Compare Two Stocks (based on PE, debt ratio, revenue growth)
5	Exit
