import signal_pipeline

print("=" * 60)
print("Signal Pipeline Python Bindings Test")
print("=" * 60)

# ---------------------------------------------------------
# Moving Average (Float)
# ---------------------------------------------------------
print("\nMovingAverageFloat")

ma = signal_pipeline.MovingAverageFloat()

samples = [1, 2, 3, 4, 5]

for s in samples:
    value = ma.update(float(s), 0.1)
    print(f"Input={s:2d}  Output={value:.3f}")

print("Filled:", ma.isFilled())

ma.reset()

# ---------------------------------------------------------
# Moving Average (Integer)
# ---------------------------------------------------------
print("\nMovingAverageInt")

mai = signal_pipeline.MovingAverageInt()

for s in samples:
    value = mai.update(s, 0.1)
    print(f"Input={s:2d}  Output={value}")

print("Filled:", mai.isFilled())

mai.reset()

# ---------------------------------------------------------
# Median Filter Float
# ---------------------------------------------------------
print("\nMedianFilterFloat")

mf = signal_pipeline.MedianFilterFloat()

samples = [5, 2, 9, 1, 4]

for s in samples:
    value = mf.update(float(s))
    print(f"Input={s:2d}  Median={value:.3f}")

print("Window Size :", mf.windowSize())
print("Sample Count:", mf.sampleCount())
print("Is Full     :", mf.isFull())

mf.reset()

# ---------------------------------------------------------
# Median Filter Integer
# ---------------------------------------------------------
print("\nMedianFilterInt")

mfi = signal_pipeline.MedianFilterInt()

for s in samples:
    value = mfi.update(s)
    print(f"Input={s:2d}  Median={value}")

print("Window Size :", mfi.windowSize())
print("Sample Count:", mfi.sampleCount())
print("Is Full     :", mfi.isFull())

mfi.reset()

# ---------------------------------------------------------
# Low Pass Filter
# ---------------------------------------------------------
print("\nLowPassFilter")

lp = signal_pipeline.LowPassFilter(2.0)

samples = [0, 10, 20, 30, 40]

for s in samples:
    value = lp.update(float(s), 0.1)
    print(f"Input={s:2d}  Output={value:.3f}")

print("Cutoff Frequency:", lp.getCutoffFrequency())

lp.reset()

# ---------------------------------------------------------
# LowPassFilterQ15
# ---------------------------------------------------------
print("\nLowPassFilterQ15")

q15 = signal_pipeline.LowPassFilterQ15()

q15.computeAlpha(2.0, 0.1)

print("Alpha Q15 =", q15.getAlphaQ15())

for s in samples:
    value = q15.update(s)
    print(f"Input={s:2d}  Output={value}")

q15.reset()

print("\n")
print("=" * 60)
print("All tests completed successfully.")
print("=" * 60)
