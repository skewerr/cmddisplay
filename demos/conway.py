"""
This is a simple implementation of Conway's Game of Life to demonstrate
cmddisplay usage. It will follow these rules:

- Live cells die if they have less than 2 or more than 3 living neighbours,
  surviving to the next generation otherwise.
- Dead cells are "born" if they have exactly 3 living neighbours, remaining
  dead on the next generation otherwise.

A single class was used: World. It inherits from Display, so it has all the
necessary methods to display what is happening. Three instance attributes were
added:

+ _gen  : The generation in which the World finds itself. Initially 0.

+ _dbuf : "death buffer", where tuples(coordinates) are stored to be deleted,
          meaning the cells in this buffer die in the next generation.

+ _bbuf : "born buffer", where tuples(coordintes) are stored to be set to
          self.fill_char, meaning the cells in this buffer are alive in the
		  next generation.

To make this more interesting, one of the three mentioned structures that
generate an infinite number of cells on the wikipedia page was used as the
initial seed, and there's a 1% chance of a random line to be spawned.

In order to keep the cells displayed at all times on fixed positions, the
showregion() method is called, rather than show(), given the latter will
display everything stored in the instance.

When applying the rules to each coordinate, only living cells and their direct
neighbours are taken into account in order to save some processing power. A
flaw in that approach, or at least the way it is implemented in this script,
is that it'll not stop itself from rechecking cells in the very likely case
there is a structure like this one:

		@
	   @

It'll check the top one and its direct neighbours, AND the bottom one and its
direct neighbours. The top one and three of its direct neighbours, includinge
the bottom cell, are checked again.

I'll try to make up for it later.
"""

from cmddisplay import Display, Pencil

import random
import time
import os

class World(Display):

	"""
	A world is a structure that contains cells. These are symbolized by
	filled pixels.
	"""

	def __init__(self):
		Display.__init__(self)

		self._gen = 0
		self._dbuf = []
		self._bbuf = []

	def tick(self):

		"""
		Goes one generation forward after applying the game rules.
		"""

		for cell in self._screen.keys():
			for x in xrange(cell[0] - 1, cell[0] + 2):
				for y in xrange(cell[1] - 1, cell[1] + 2):
					self._apply_rules((x, y))

		self._clear_buffers()
		self._gen += 1

	def _apply_rules(self, cell):

		"""
		Applies the game rules to a cell.
		"""

		assert type(cell) is tuple and len(cell) == 2 and \
			type(cell[0]) is int and type(cell[1]) is int, \
			"Cells are tuples of two integers."

		neighbour_count = self._count_neighbours(cell)

		if cell in self._screen:
			if neighbour_count < 2 or neighbour_count > 3:
				self._dbuf.append(cell)

		else:
			if neighbour_count == 3:
				self._bbuf.append(cell)

	def _count_neighbours(self, cell):

		"""
		Counts the number of live cells that neighbour a cell.
		"""

		assert type(cell) is tuple and len(cell) == 2 and \
			type(cell[0]) is int and type(cell[1]) is int, \
			"Cells are tuples of two integer."

		neighbour_count = 0

		for x in xrange(cell[0] - 1, cell[0] + 2):
			for y in xrange(cell[1] - 1, cell[1] + 2):
				if (x, y) in self._screen and (x, y) != cell:
					neighbour_count += 1

		return neighbour_count

	def _clear_buffers(self):

		"""
		Applies operations to this object's buffers, clearing them.
		"""

		for cell in self._dbuf:
			self.empty(cell[0], cell[1])

		for cell in self._bbuf:
			self.fill(cell[0], cell[1])

		self._dbuf = []
		self._bbuf = []


if __name__ == "__main__":

	w = World()
	p = Pencil(w)

	# Initial seed.
	for _ in xrange(-60, -52):
		w.fill(_, 0)

	for _ in xrange(-51, -46):
		w.fill(_, 0)

	for _ in xrange(-43, -40):
		w.fill(_, 0)

	for _ in xrange(-34, -27):
		w.fill(_, 0)

	for _ in xrange(-26, -21):
		w.fill(_, 0)

	# Main loop.
	while True:
		print "\033[0;0f"
		w.showregion(-100, -27, 100, 27)
		w.tick()

		# Random line.
		if not random.randint(0, 100):
			p.drawline(random.randint(-100, 101), random.randint(-27, 28),
				random.randint(-100, 101), random.randint(-27, 28))

