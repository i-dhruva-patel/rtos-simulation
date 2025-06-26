import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

# Load with 'missed' column
df = pd.read_csv("trace.csv", names=["Task", "StartTime", "Duration", "Missed"])
df["StartTime"] = df["StartTime"] - df["StartTime"].min()

# Unique tasks and Y positions
tasks = list(df["Task"].unique())
task_y = {task: i * 10 for i, task in enumerate(tasks)}

# Setup plot
fig, ax = plt.subplots(figsize=(14, 6))

# Plot each task instance
for _, row in df.iterrows():
    color = "red" if row["Missed"] else {"T1": "tab:blue", "T2": "orange", "T3": "green"}[row["Task"]]
    label = f"{int(row['Duration'])} ms"

    ax.broken_barh([(row["StartTime"], row["Duration"])],
                   (task_y[row["Task"]], 9),
                   facecolors=color)

    # Label bars
    ax.text(row["StartTime"] + 5, task_y[row["Task"]] + 2, label,
            fontsize=8, color="white" if color == "red" else "black")

    if row["Missed"]:
        ax.text(row["StartTime"], task_y[row["Task"]] + 8, "Miss",
                fontsize=7, color="red")

# Axis styling
ax.set_xlabel("Time (ms)")
ax.set_yticks([v + 4.5 for v in task_y.values()])
ax.set_yticklabels(task_y.keys())
ax.set_title("Task Execution Gantt Chart with Deadline Misses")
ax.grid(True)

# Legend
from matplotlib.patches import Patch
legend = [
    Patch(color="tab:blue", label="T1"),
    Patch(color="orange", label="T2"),
    Patch(color="green", label="T3"),
    Patch(color="red", label="Deadline Miss")
]
ax.legend(handles=legend, loc="lower right")

# Save to file
filename = f"gantt_{datetime.now().strftime('%Y%m%d_%H%M%S')}.png"
plt.savefig(filename)
print(f"✅ Chart saved as {filename}")

