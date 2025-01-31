# Schema hints configuration
In .vscode/*.code-workspace add following code into "settings"
```json
"json.schemas": [
    {"fileMatch": ["*items.json"], "url": "../schema/items.schema.json"}
]
```