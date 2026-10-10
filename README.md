# Odysseus parser demo

A real GitHub repository containing synthetic fixtures for Odysseus ingestion.
Use the real GitHub adapter, without the --mock flag.

## Build and run

```sh
mkdir -p build
c++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/calculator.cpp -o build/demo
./build/demo
```

Expected output:

```text
Score: 10
imaginary_call() is only text
```

## Expected ingestion

With exactly these files, expect 6 stored artifacts and 2 skipped files
(.gitignore and data/ignored.json). Three artifacts are code and three are
documents: README.md, docs/notes.md, and docs/empty.txt.

Expected code extraction across the three code files:

- Classes/structs: Score and Calculator.
- Function definitions: Calculator::total, add, twice, and main.
- Includes: calculator.hpp in calculator.cpp; iostream and calculator.hpp in main.cpp.
- Calls: Calculator::total -> add; twice -> add; main -> total; main -> twice.
- No FakeClass, fake_function, fake_call, or imaginary_call symbols from comments or strings.
- Function declarations in the header should not become function definitions.

Calls currently use bare callee names; this fixture does not assert complete
cross-file or C++ semantic name resolution.

The empty text file should still be stored in PostgreSQL. It produces no vector
points. Unicode in docs/notes.md should be preserved.

## End-to-end run

From the Odysseus project, with ODYSSEUS_DATABASE_URL configured:

```sh
./build/ingestion/odysseus ingest github https://github.com/OWNER/odysseus-parser-demo --postgres
./build/ingestion/odysseus-index all
```

Replace OWNER with your GitHub account. PostgreSQL ingestion queues 12 tasks
(one vector and one graph task per artifact). The worker processes other ready
tasks in the same database too. Qdrant and Neo4j require their services to be
running; vector indexing also requires Ollama and the embedding model.

To test updates, change the Unicode notes, commit, push, and ingest again.
A new commit is a new revision: old revision artifacts remain stored.
