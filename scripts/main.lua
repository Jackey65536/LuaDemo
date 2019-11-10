version = 2.1
name = "lua"

people = {
    name = "zhangsan",
    age = 20,
    com = "xl"
}

function getPeopleInfo()
    return people.name, people.age
end

function getString(name)
    return "hello "..name
end

function main()
    print("hello")
end