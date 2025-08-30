import yfinance as yf
import pandas as pd

# List of Nifty 50 tickers
nifty50_tickers = [
    "ADANIPORTS.NS","ASIANPAINT.NS","AXISBANK.NS","BAJAJ-AUTO.NS","BAJFINANCE.NS",
    "BAJAJFINSV.NS","BPCL.NS","BHARTIARTL.NS","BRITANNIA.NS","CIPLA.NS",
    "COALINDIA.NS","DRREDDY.NS","EICHERMOT.NS","GRASIM.NS","HCLTECH.NS",
    "HDFC.NS","HDFCBANK.NS","HDFCLIFE.NS","HEROMOTOCO.NS","HINDALCO.NS",
    "HINDUNILVR.NS","ICICIBANK.NS","INDUSINDBK.NS","INFY.NS","IOC.NS",
    "ITC.NS","JSWSTEEL.NS","KOTAKBANK.NS","LT.NS","M&M.NS",
    "MARUTI.NS","NESTLEIND.NS","NTPC.NS","ONGC.NS","POWERGRID.NS",
    "RELIANCE.NS","SBILIFE.NS","SBIN.NS","SHREECEM.NS","SUNPHARMA.NS",
    "TCS.NS","TATACONSUM.NS","TATAMOTORS.NS","TATASTEEL.NS","TECHM.NS",
    "TITAN.NS","ULTRACEMCO.NS","UPL.NS","WIPRO.NS"
]

data_list = []

for ticker in nifty50_tickers:
    stock = yf.Ticker(ticker)
    info = stock.info

    # Skip if no previous close
    if 'previousClose' not in info:
        continue

    # Historical prices (last 5 days)
    hist = stock.history(period="5d")['Close'].tolist()
    while len(hist) < 5:
        hist.append(info['previousClose'])

    # Financials
    pe = info.get('trailingPE', 0.0)
    debt_ratio = (info.get('totalDebt', 0.0) / info.get('totalAssets', 1.0))
    rev_growth = info.get('revenueGrowth', 0.0)
    profit_margin = info.get('profitMargins', 0.0)
    roe = info.get('returnOnEquity', 0.0)

    # Revenue and profit past 5 years (if not available, duplicate current)
    revenue_history = [info.get('totalRevenue', 0.0)] * 5
    profit_history = [info.get('netIncome', 0.0)] * 5

    row = [ticker] + hist + [pe, debt_ratio, rev_growth, profit_margin, roe] + revenue_history + profit_history
    data_list.append(row)

# Create DataFrame
columns = ['Name', 'Price1', 'Price2', 'Price3', 'Price4', 'Price5',
           'PE', 'DebtRatio', 'RevenueGrowth', 'ProfitMargin', 'ROE',
           'Revenue5', 'Revenue4', 'Revenue3', 'Revenue2', 'Revenue1',
           'Profit5', 'Profit4', 'Profit3', 'Profit2', 'Profit1']

df = pd.DataFrame(data_list, columns=columns)

# Save CSV
df.to_csv('nifty50_full_5yr.csv', index=False)
print("CSV created: nifty50_full_5yr.csv")
