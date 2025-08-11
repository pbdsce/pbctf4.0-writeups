# PB's Time Lore Challenge Writeup

## Challenge Description
> PB has built a knowledge base cataloguing everything from causal loops to movie plots and iconic quotes. Their system only accepts queries as **numerical vectors**
>  
> Word is that their research uncovered some particularly memorable lines from sci-fi timetravel classics.
>  

The database contains a large corpus of **time travel-related content** (movie scripts, iconic quotes, scientific theories).  
However, the search API does **not** accept plain text — it only takes **384-dimensional embedding vectors**.

Our task:  
Find the **most famous line from The Terminator**, "I'll be back," was originally scripted as **"I'll come back"**

---

## We were given:
- **Challenge URL:** `https://time-lore.pbctf.live/`
- A UI with **only an embedding vector input** field (no raw text search).
- Database contains **time travel media** quotes.
- Model used for vector search: `all-MiniLM-L6-v2` (384-dimensional embeddings).

Key observation:
- Since the query field only accepts embeddings, we need to **generate the vector for the target quote** using the same embedding model as the database.

---

## Exploitation Steps

1. **Identify the Embedding Model**
   - Challenge hints and metadata indicated the use of any  **384-dim embedding model**.

2. **Generate the Target Embedding**
   ```python
   from sentence_transformers import SentenceTransformer

   # Load the same embedding model used by the backend
   model = SentenceTransformer('all-MiniLM-L6-v2')

   # Famous Terminator quote
   text = "I'll come back"

   # Generate embedding (384 floats)
   embedding = model.encode(text)

   print(embedding.tolist())  # To paste into the challenge UI

3. **Search using embeddings**

![Search in UI](misc/PB's_Time_Lore/images/search.png)

**Flag:** `pbctf{v3c70r_db_1s_g00d}`
