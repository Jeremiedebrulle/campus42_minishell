### 🧭 Git Collaboration Protocol

> **Purpose:** Ensure smooth, conflict-free collaboration between team members working on separate parts of the project.

---

### 📌 General Principles

1. **Do not commit directly to `master`.**
   All development work must be done in feature branches.

2. **Each teammate works in their own branch**, named using the pattern:

   ```
   yourname-feature-name
   ```

3. **Commit regularly** to document your progress and enable easy troubleshooting or rollbacks.

---

### 🔄 Daily Workflow

1. **Before starting work:**

   ```bash
   git pull origin master
   ```

2. **Switch to your feature branch** or create it if necessary:

   ```bash
   git checkout -b yourname-feature-name
   ```

3. **Work and commit locally:**

   ```bash
   git add .
   git commit -m "Clear and brief description of your change"
   ```

4. **Push your changes** regularly to back up your work:

   ```bash
   git push origin yourname-feature-name
   ```

---

### 🔁 Merging and Synchronization

* **Do not merge to `master` until your feature is ready.**
* **No daily merging required** if teammates are working on isolated parts.
* When your work is complete:

  1. Sync your branch with `master` to resolve any potential conflicts:

     ```bash
     git checkout yourname-feature
     git pull origin master
     ```

  2. Merge your branch into `master`:

     ```bash
     git checkout master
     git pull origin master
     git merge yourname-feature
     git push origin master
     ```

  3. Optionally delete the feature branch:

     ```bash
     git branch -d yourname-feature
     git push origin --delete yourname-feature
     ```

---

### 🧠 Recommendations

* **Communicate with your teammate** before merging to `master`, especially if your changes affect shared files or logic.
* **Merge frequently enough** to avoid large, painful conflicts, but only when the feature is ready or needs integration.

---
