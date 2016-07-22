/**
 * Created by KICT-22 on 2016-07-19.
 */

let array_test = [
    {
        name: 'so',
        hp: 52
    },
    {
        name: 'sfo',
        hp: 88
    },
    {
        name: 'sog',
        hp: 32
    },
    {
        name: 'sodd',
        hp: 62
    }
];

console.log(array_test);
array_test.sort((left,right)=> {
    return left.hp - right.hp;
});
console.log('--------------');
console.log(array_test);