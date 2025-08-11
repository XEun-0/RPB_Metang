def simulate_payoff(balance, apr, monthly_min, extra_payment=0):
    month = 0
    total_interest = 0.0
    balance = float(balance)
    apr_monthly = apr / 100 / 12
    MAX_MONTHS = 600  # 50 years limit

    print(f"Starting payoff simulation:")
    print(f"Balance: ${balance:.2f}, APR: {apr}%, Minimum Payment: ${monthly_min:.2f}, Extra Payment: ${extra_payment:.2f}")
    print("-" * 75)
    print(f"{'Month':<6}{'Start Bal':<12}{'Interest':<10}{'Payment':<10}{'End Bal':<12}")

    while balance > 0 and month < MAX_MONTHS:
        month += 1
        interest = balance * apr_monthly
        total_interest += interest
        balance += interest

        # Check if payment covers interest + a bit to reduce principal (say 1% of balance or $10, whichever is higher)
        min_needed = interest + max(balance * 0.01, 10)

        payment = monthly_min + extra_payment
        if payment < min_needed:
            print(f"\n*** WARNING ***")
            print(f"Payment (${payment:.2f}) is too low to reduce balance.")
            print(f"Minimum suggested payment to reduce principal: ${min_needed:.2f}")
            print(f"Adjusting payment to minimum suggested payment.\n")
            payment = min_needed

        if payment > balance:
            payment = balance  # final payment

        balance -= payment

        print(f"{month:<6}{balance + payment - interest:<12.2f}{interest:<10.2f}{payment:<10.2f}{max(balance,0):<12.2f}")

    if balance > 0:
        print(f"Stopped after {month} months with remaining balance: ${balance:.2f}")
    else:
        print("-" * 75)
        print(f"Paid off in {month} months, total interest paid: ${total_interest:.2f}")
    print()
    return month, total_interest



cards = [
    {"balance": 3884.11, "apr": 27.99, "min_payment": 70},
    {"balance": 9355.79, "apr": 27.49, "min_payment": 278},
    {"balance": 3442.97, "apr": 27.0,  "min_payment": 64},
]

for i, card in enumerate(cards, start=1):
    print(f"--- Card #{i} ---")
    simulate_payoff(card["balance"], card["apr"], card["min_payment"])

