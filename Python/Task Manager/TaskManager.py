import json

class Task:
    def __init__(self, title):
        self.title = title
        self.is_done = False

    def mark_done(self):
        self.is_done = True

class TaskManager:
    def __init__(self):
        self.tasks = []
        try:
            self.load_tasks()
        except:
            print("No tasks to load")

    def add_task(self, title):
        new_task = Task(title)
        self.tasks.append(new_task)

    def show_tasks(self):
        i = 0
        for t in self.tasks:
            print(f"{i}.{t.title} {t.is_done} ")
            i += 1

    def get_stats(self):
        stats = {
            "completed" : 0,
            "pending" : 0,
            "length" : len(self.tasks)
        }
        for i in self.tasks:
            if i.is_done == True:
                stats["completed"] += 1
            else:
                stats["pending"] += 1
        return stats
    
    def save_tasks(self):
        export_list = []
        for i in self.tasks:
            export_list.append( {
                "title" : i.title,
                "is_done" : i.is_done
            })
        with open ("tasks.json", "w") as file:
            json.dump(export_list, file)
        
    def load_tasks(self):
        with open("tasks.json", "r") as file:
            saved_data = json.load(file)
            for i in saved_data:
                new_task = Task(i["title"])
                if i["is_done"] == True: new_task.mark_done()
                self.tasks.append(new_task)

    def clear_tasks(self):
        self.tasks = []
        with open("tasks.json", "w") as file:
            json.dump(self.tasks, file)

manager = TaskManager()
while True:
    action = input("What would you like to do? (add/show/finish/stats/save/clear/quit) \n")
    if action.lower() == "add":
        title = input("Enter your task\n")
        manager.add_task(title)
    elif action.lower() == "show":
        manager.show_tasks()
    elif action.lower() == "finish":
        manager.show_tasks()
        number = input("Choose the task number\n") #I will assume the user inputs only numbers due to this being practice
        manager.tasks[int(number)].mark_done()
    elif action.lower() == "stats":
        stats = manager.get_stats()
        print (stats)
    elif action.lower() == "save":
        manager.save_tasks()
    elif action.lower() == "clear":
        manager.clear_tasks()
    elif action.lower() == "quit":
        break
    else:
        print("Please input a valid option")