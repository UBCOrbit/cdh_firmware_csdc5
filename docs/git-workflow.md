# Git Workflow

All changes to this repository will go through pull requests, so that
they can be organized and reviewed separately.

To get started, fork the repo (into your personal account).  Then,
clone the repository, recursively:

```
git clone --recursive git@github.com:your-user/cdh_firmware_csdc5.git
```

Now, `origin` points to your fork of the repo, but we'll set up
`upstream` to point to the main repo so you can synchronize with it.

```
git remote add upstream https://github.com/UBCOrbit/cdh_firmware_csdc5.git
```

## Creating a pull-request!

Commit your changes, as usual:

```
git add -A
git commit -m "Described your changes here"
git push origin master
```

Then, create a pull request on the main repo and write a description
for it.

## Synchronizing your Fork with Upstream

If some new changes have been introduced upstream, and you want to
bring your fork up-to-date with them, it's as simple as:

```
git pull --rebase upstream master
git push origin master
```
