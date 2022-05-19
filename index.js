// Can you crack the code solver
String.prototype.pow = function (n) {
  let o = "";
  for (let i = 0; i < n; i++) o += this;
  return o;
};

const _ = require("lodash");
const rls = require("readline-sync");

function allPossibleCombinations(input, length, curstr) {
  if (curstr.length == length) return [curstr];
  var ret = [];
  for (var i = 0; i < input.length; i++) {
    ret.push.apply(
      ret,
      allPossibleCombinations(input, length, curstr + input[i])
    );
  }
  return ret;
}
function checkAndExit(prop) {
  if (prop.length == 1) {
    console.log("Result:", prop[0]);
    process.exit(0);
  }
}

let amount = rls.questionInt("Key length: ");
let nonright = rls.question("Code with no right: ").split("");

if (nonright.length != amount) {
  console.error("Wrong key length");
  process.exit(1);
} else if (_.some(nonright, (el) => /[^0-9]/.test(el))) {
  console.error("Wrong key: key can be only numbers");
  process.exit(1);
} else if (_.uniq(nonright).length != amount) {
  console.error("Wrong key: key numbers must be unique");
  process.exit(1);
}

let orpr = rls
  .question("Code with " + (amount - 2) + " right number and position: ")
  .split("");

if (orpr.length != amount) {
  console.error("Wrong key length");
  process.exit(1);
} else if (_.some(orpr, (el) => /[^0-9]/.test(el))) {
  console.error("Wrong key: key can be only numbers");
  process.exit(1);
} else if (_.uniq(orpr).length != amount) {
  console.error("Wrong key: key numbers must be unique");
  process.exit(1);
}

let orwp1 = rls
  .question("Code with " + (amount - 2) + " right number and wrong position: ")
  .split("");

if (orwp1.length != amount) {
  console.error("Wrong key length");
  process.exit(1);
} else if (_.some(orwp1, (el) => /[^0-9]/.test(el))) {
  console.error("Wrong key: key can be only numbers");
  process.exit(1);
} else if (_.uniq(orwp1).length != amount) {
  console.error("Wrong key: key numbers must be unique");
  process.exit(1);
}

let orwp2 = rls
  .question(
    "Second code with " + (amount - 2) + " right number and wrong position: "
  )
  .split("");

if (orwp2.length != amount) {
  console.error("Wrong key length");
  process.exit(1);
} else if (_.some(orwp2, (el) => /[^0-9]/.test(el))) {
  console.error("Wrong key: key can be only numbers");
  process.exit(1);
} else if (_.uniq(orwp2).length != amount) {
  console.error("Wrong key: key numbers must be unique");
  process.exit(1);
}

let trwp = rls
  .question("Code with " + (amount - 1) + " right number and wrong position: ")
  .split("");

if (trwp.length != amount) {
  console.error("Wrong key length");
  process.exit(1);
} else if (_.some(trwp, (el) => /[^0-9]/.test(el))) {
  console.error("Wrong key: key can be only numbers");
  process.exit(1);
} else if (_.uniq(trwp).length != amount) {
  console.error("Wrong key: key numbers must be unique");
  process.exit(1);
}

let rep_sym = "*";

// Step 1: remove non right:

orpr = _.join(orpr, "")
  .replace(new RegExp("" + _.join(nonright, "|"), "g"), rep_sym)
  .split("");
orwp1 = _.join(orwp1, "")
  .replace(new RegExp("" + _.join(nonright, "|"), "g"), rep_sym)
  .split("");
orwp2 = _.join(orwp2, "")
  .replace(new RegExp("" + _.join(nonright, "|"), "g"), rep_sym)
  .split("");
trwp = _.join(trwp, "")
  .replace(new RegExp("" + _.join(nonright, "|"), "g"), rep_sym)
  .split("");

// Recheck rules:
if (_.filter(orpr, (el) => el != rep_sym).length < amount - 2) {
  console.error('Wrong key: Rule "One right, position right" is wrong');
  process.exit(1);
}
if (_.filter(orwp1, (el) => el != rep_sym).length < amount - 2) {
  console.error('Wrong key: Rule "One right, position wrong" is wrong');
  process.exit(1);
}
if (_.filter(orwp2, (el) => el != rep_sym).length < amount - 2) {
  console.error('Wrong key: Rule "One right, position wrong" is wrong');
  process.exit(1);
}
if (_.filter(trwp, (el) => el != rep_sym).length < amount - 1) {
  console.error('Wrong key: Rule "Two right, position wrong" is wrong');
  process.exit(1);
}

orpr = _.map(orpr, (el, k) => {
  if (el != rep_sym) {
    if (el == orwp1[k] || el == orwp2[k] || el == trwp[k]) {
      let rm = el;
      _.indexOf(orwp1, el) != -1 && (orwp1[_.indexOf(orwp1, el)] = rep_sym);
      _.indexOf(orwp2, el) != -1 && (orwp2[_.indexOf(orwp2, el)] = rep_sym);
      _.indexOf(trwp, el) != -1 && (trwp[_.indexOf(trwp, el)] = rep_sym);
      return "*";
    }
  }
  return el;
});

let left = _.filter(
  _.uniq([...orpr, ...orwp1, ...orwp2, ...trwp]),
  (el) => el != rep_sym
).sort();
let all_posible = _.filter(
  allPossibleCombinations(left, amount, ""),
  (el) => _.uniq(el.split("")).length == amount
);
all_posible = _.filter(all_posible, (el) => {
  let inc = false;
  for (let i = 0; i < amount; i++) {
    inc = inc || orpr[i] == el[i];
  }
  return inc;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  let inc = 0;
  for (let i = 0; i < amount; i++) {
    if (_.includes(_.split(el, ""), trwp[i])) inc++;
  }
  return inc == amount - 1;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  let inc = 0;
  for (let i = 0; i < amount; i++) {
    if (_.includes(_.split(el, ""), orwp1[i])) inc++;
  }
  return inc == amount - 2;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  let inc = 0;
  for (let i = 0; i < amount; i++) {
    if (_.includes(_.split(el, ""), orwp2[i])) inc++;
  }
  return inc == amount - 2;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  let inc = 0;
  for (let i = 0; i < amount; i++) {
    if (el[i] === orpr[i]) inc++;
  }
  return inc == amount - 2;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  for (let i = 0; i < amount; i++) {
    if (el[i] == trwp[i]) return false;
  }
  return true;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  for (let i = 0; i < amount; i++) {
    if (el[i] == orwp1[i]) return false;
  }
  return true;
});
checkAndExit(all_posible);
all_posible = _.filter(all_posible, (el) => {
  for (let i = 0; i < amount; i++) {
    if (el[i] == orwp2[i]) return false;
  }
  return true;
});
checkAndExit(all_posible);
