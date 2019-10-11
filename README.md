# bananas

## Notes

- Basically, typeclasses come from Category theory.
- A category is something that has composable (can be combined together)
  morphisms (function-like ideas that are not as strict).
- All fns are morphisms.
- Regular string concatenations are morphisms but not strictly functions
  because they don't obey all fn laws.
- All mathema. fns that are transitive, ... are invertible.
- Logic, fns in a mathematical prog lang e.g. haskell, ocaml, prolog etc. are COMPLETELY different from the ones
  found in business langs e.g. python etc.
- e.g. logic in math langs need to have both if and else defined but not in
  regular langs.

---

[![CircleCI](https://circleci.com/gh/yourgithubhandle/bananas/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/bananas/tree/master)

**Contains the following libraries and executables:**

```
bananas@0.0.0
│
├─test/
│   name:    TestBananas.exe
│   main:    TestBananas
│   require: bananas.lib
│
├─library/
│   library name: bananas.lib
│   namespace:    Bananas
│   require:
│
└─executable/
    name:    BananasApp.exe
    main:    BananasApp
    require: bananas.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x BananasApp.exe
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
