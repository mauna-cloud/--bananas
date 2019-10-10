# bananas


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
