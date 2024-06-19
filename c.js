const { execSync } = require("child_process");
const fs = require("fs");
const path = require("path");

let files = fs.readdirSync(__dirname).filter((f) => !/.*\.js.*/.test(f));

files = files
  .map((f) => {
    const filePath = path.join(__dirname, f);
    if (fs.lstatSync(filePath).isDirectory()) return null;
    return { f, m: fs.statSync(filePath).mtime };
  })
  .filter((f) => f);

files.sort((a, b) => new Date(a.m).getTime() - new Date(b.m).getTime());

console.table(files);

const createCommitMessage = (fileName, isGrouped) => {
  if (isGrouped) {
    fileName = fileName.split(".")[0];
  }
  const messages = [fileName, `added ${fileName}`, `create ${fileName}`];
  return `"${messages[Math.floor(Math.random() * messages.length)]}"`;
};

const datestring = (d) =>
  ("0" + d.getDate()).slice(-2) +
  "-" +
  ("0" + (d.getMonth() + 1)).slice(-2) +
  "-" +
  d.getFullYear() +
  " " +
  ("0" + d.getHours()).slice(-2) +
  ":" +
  ("0" + d.getMinutes()).slice(-2) +
  ":" +
  ("0" + d.getSeconds()).slice(-2);

const applyCommits = async () => {
  for (let i = 0; i < files.length; i++) {
    let k = -1;
    do {
      console.log(`git add ${files[i].f}`);
      execSync(`git add ${files[i].f}`);
      await new Promise((resolve) => setTimeout(resolve, 100));
      i++;
      k++;
    } while (
      i < files.length &&
      files[i].f.split(".")[0] === files[i + 1]?.f.split(".")[0]
    );
    i--;
    // console.log(datestring(files[i].m));
    execSync(
      `git commit -m ${createCommitMessage(
        files[i].f,
        Boolean(k)
      )} --date="${datestring(files[i].m)}"`
    );
    await new Promise((resolve) => setTimeout(resolve, 100));
  }
};

applyCommits();
