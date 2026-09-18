import ollama
import sys

# Topic from user or example argument if empty
topic = sys.argv[1] if len(sys.argv) > 1 else "whether a hot dog is a sandwich"

# PERSONALITIES
provocateur_prompt = (
    f"You are a master provocateur debating '{topic}'. Your goal is to wind up your opponent "
    "with absurd comparisons, playful insults, and deliberate misrepresentations of their arguments. "
    "Be witty, sarcastic, and infuriatingly smug. Never swear or use hate speech."
)

earnest_prompt = (
    f"You are a well-meaning but extremely sensitive person debating '{topic}'. "
    "You take every statement literally and personally. You are easily baited, quick to become defensive, "
    "and respond with long, passionate, often off-topic rebuttals. You genuinely want a civil discussion "
    "but cannot resist rising to provocation."
)

# Start the fight
history = []

# Provocateur opens
resp = ollama.chat(model="phi3", messages=[
    {"role": "system", "content": provocateur_prompt},
    {"role": "user", "content": "Kick off the debate with a provocative opening statement."}
])
print(f"\033[91mPROVOCATEUR:\033[0m {resp['message']['content']}")
history.append(("PROVOCATEUR", resp['message']['content']))

# 10 prompts
for _ in range(10):
    # Earnest responds
    last = history[-1][1]
    resp = ollama.chat(model="phi3", messages=[
        {"role": "system", "content": earnest_prompt},
        {"role": "user", "content": f"Respond to: '{last}'"}
    ])
    print(f"\033[94mEARNEST:\033[0m {resp['message']['content']}")
    history.append(("EARNEST", resp['message']['content']))

    # Provocateur responds
    last = history[-1][1]
    resp = ollama.chat(model="phi3", messages=[
        {"role": "system", "content": provocateur_prompt},
        {"role": "user", "content": f"Respond to: '{last}'"}
    ])
    print(f"\033[91mPROVOCATEUR:\033[0m {resp['message']['content']}")
    history.append(("PROVOCATEUR", resp['message']['content']))

# Save transcript
with open("transcript.txt", "w", encoding="utf-8") as f:
    f.write(f"BOT FIGHT — Topic: {topic}\n\n")
    for speaker, msg in history:
        f.write(f"{speaker}: {msg}\n\n")

print(f"\nTranscript saved to transcript.txt. The bots have exhausted themselves.")