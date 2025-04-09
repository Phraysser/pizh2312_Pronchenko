import pygame
import random
import sys
import os


WINDOW_WIDTH = 600
WINDOW_HEIGHT = 400
CELL_SIZE = 20


WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLACK = (0, 0, 0)

RECORD_FILE = "record.txt"


class GameObject:
    def __init__(self, position, body_color):
        self.position = position
        self.body_color = body_color

    def draw(self, surface):
        pygame.draw.rect(surface, self.body_color, pygame.Rect(
            self.position[0], self.position[1], CELL_SIZE, CELL_SIZE))


class Apple(GameObject):
    def __init__(self):
        self.body_color = RED
        self.position = [0, 0]
        self.randomize_position()

    def randomize_position(self):
        self.position = [
            random.randint(0, (WINDOW_WIDTH - CELL_SIZE) // CELL_SIZE) * CELL_SIZE,
            random.randint(0, (WINDOW_HEIGHT - CELL_SIZE) // CELL_SIZE) * CELL_SIZE
        ]

    def draw(self, surface):
        super().draw(surface)


class Snake(GameObject):
    def __init__(self):
        self.length = 1
        self.positions = [[100, 100]]
        self.direction = [CELL_SIZE, 0]
        self.next_direction = [CELL_SIZE, 0]
        self.body_color = GREEN

    def update_direction(self, new_dir):
        opposite = [-self.direction[0], -self.direction[1]]
        if new_dir != opposite:
            self.next_direction = new_dir

    def move(self):
        self.direction = self.next_direction
        head = self.get_head_position()
        new_head = [head[0] + self.direction[0], head[1] + self.direction[1]]
        new_head[0] %= WINDOW_WIDTH
        new_head[1] %= WINDOW_HEIGHT

        self.positions.insert(0, new_head)

        if len(self.positions) > self.length:
            self.positions.pop()

    def draw(self, surface):
        for pos in self.positions:
            pygame.draw.rect(surface, self.body_color, pygame.Rect(pos[0], pos[1], CELL_SIZE, CELL_SIZE))

    def get_head_position(self):
        return self.positions[0]

    def grow(self):
        self.length += 1

    def reset(self):
        self.length = 1
        self.positions = [[100, 100]]
        self.direction = [CELL_SIZE, 0]
        self.next_direction = [CELL_SIZE, 0]

    def check_self_collision(self):
        return self.get_head_position() in self.positions[1:]


def load_record():
    if os.path.exists(RECORD_FILE):
        with open(RECORD_FILE, "r") as f:
            return int(f.read())
    return 0


def save_record(record):
    with open(RECORD_FILE, "w") as f:
        f.write(str(record))


def main():
    pygame.init()
    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("Змейка")
    clock = pygame.time.Clock()
    font = pygame.font.SysFont(None, 36)

    snake = Snake()
    apple = Apple()
    score = 0
    record = load_record()
    running = True

    while running:
        clock.tick(10)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                elif event.key == pygame.K_UP:
                    snake.update_direction([0, -CELL_SIZE])
                elif event.key == pygame.K_DOWN:
                    snake.update_direction([0, CELL_SIZE])
                elif event.key == pygame.K_LEFT:
                    snake.update_direction([-CELL_SIZE, 0])
                elif event.key == pygame.K_RIGHT:
                    snake.update_direction([CELL_SIZE, 0])
        snake.move()

        if snake.get_head_position() == apple.position:
            snake.grow()
            apple.randomize_position()
            score += 1

        if snake.check_self_collision():
            if score > record:
                record = score
                save_record(record)
            snake.reset()
            score = 0

        screen.fill(BLACK)
        snake.draw(screen)
        apple.draw(screen)
        score_text = font.render(f"Cчёт: {score}  Рекорд: {record}", True, WHITE)
        screen.blit(score_text, (10, 10))
        pygame.display.flip()

    if score > record:
        save_record(score)

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
