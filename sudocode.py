leftSensor = Sensor()
rightSensor = Sensor()

leftSensorPrevColor = leftSensor.getColor()
rightSensorPrevColor = leftSensor.getColor()

lastTransition = 0
lastTransitionSensor = None

# max time in ms since last transition to consider sensors on same height, so that vehicle is driving straight to center
transitionThreshold = 100

loopDelay = 50 # time in ms to wait before race logic loop continues

# marks a turn around action, when driving away from center was detected
changesDirection = False

def main():
	while True:
		delay(50)

		# when vehicle is turning around at the moment, do not trigger other events
		if changesDirection:
			continue

		# right sensor detection
		# vehicle potentially driving to central axis

		if (((rightSensor.getColor() == "black" and rightSensorPrevColor == "white")
			or (rightSensor.getColor() == "grey" and rightSensorPrevColor == "black")
			or (rightSensor.getColor == "white" and rightSensorPrevColor == "grey"))
			and leftSensor.getColor() == rightSensorPrevColor):

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != rightSensor):
				lastTransitionSensor = rightSensor
				lastTransition = time.time()
				continue

			lastTransition = time.time()
			turnRight()

		if ((rightSensor.getColor() == "black" and rightSensorPrevColor == "white")
			or (rightSensor.getColor() == "grey" and rightSensorPrevColor == "black")
			or (rightSensor.getColor == "white" and rightSensorPrevColor == "grey"))
			and leftSensor.getColor() == rightSensor.getColor():

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != rightSensor):
				lastTransitionSensor = rightSensor
				lastTransition = time.time()
				continue

			lastTransition = time.time()
			turnLeft()


		# left sensor detection
		# vehicle potentially driving to central axis

		if ((leftSensor.getColor() == "black" and leftSensorPrevColor == "white")
			or (leftSensor.getColor() == "grey" and leftSensorPrevColor == "black")
			or (leftSensor.getColor == "white" and leftSensorPrevColor == "grey"))
			and rightSensor.getColor() == leftSensorPrevColor:

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != leftSensor):
				lastTransitionSensor = leftSensor
				lastTransition = time.time()
				continue

			lastTransition = time.time()
			trunLeft()

		if ((leftSensor.getColor() == "black" and leftSensorPrevColor == "white")
			or (leftSensor.getColor() == "grey" and leftSensorPrevColor == "black")
			or (leftSensor.getColor == "white" and leftSensorPrevColor == "grey"))
			and rightSensor.getColor() == leftSensor.getColor():

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != leftSensor):
				lastTransitionSensor = leftSensor
				lastTransition = time.time()
				continue
				
			lastTransition = time.time()
			turnRight()

		# right sensor detection
		# vehicle potentially driving away from center

		if ((rightSensor.getColor() == "grey" and rightSensorPrevColor == "white")
			or (rightSensor.getColor() == "black" and rightSensorPrevColor == "grey")
			or (rightSensor.getColor == "white" and rightSensorPrevColor == "black"))
			and leftSensor.getColor() == rightSensorPrevColor:

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != rightSensor):
				lastTransitionSensor = rightSensor
				lastTransition = time.time()
				turn180()
				changesDirection = True
				continue

			changesDirection = True
			lastTransition = time.time()
			turnStrongerLeft()

		if ((rightSensor.getColor() == "grey" and rightSensorPrevColor == "white")
			or (rightSensor.getColor() == "black" and rightSensorPrevColor == "grey")
			or (rightSensor.getColor == "white" and rightSensorPrevColor == "black"))
			and leftSensor.getColor() == rightSensor.getColor():

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != rightSensor):
				lastTransitionSensor = rightSensor
				lastTransition = time.time()
				turn180()
				changesDirection = True
				continue

			changesDirection = True
			lastTransition = time.time()
			turnStrongerRight()

		# left sensor detection
		# vehicle potentially driving away from center

		if ((leftSensor.getColor() == "grey" and leftSensorPrevColor == "white")
			or (leftSensor.getColor() == "black" and leftSensorPrevColor == "grey")
			or (leftSensor.getColor == "white" and leftSensorPrevColor == "black"))
			and rightSensor.getColor() == leftSensorPrevColor:

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != leftSensor):
				lastTransitionSensor = leftSensor
				lastTransition = time.time()
				turn180()
				changesDirection = True
				continue

			changesDirection = True
			lastTransition = time.time()
			turnStrongerRight()

		if ((leftSensor.getColor() == "grey" and rightSensorPrevColor == "white")
			or (leftSensor.getColor() == "black" and rightSensorPrevColor == "grey")
			or (leftSensor.getColor == "white" and rightSensorPrevColor == "black"))
			and rightSensor.getColor() == leftSensor.getColor():

			if(time.time() - lastTransition < transitionThreshold and lastTransitionSensor != rightSensor):
				lastTransitionSensor = rightSensor
				lastTransition = time.time()
				turn180()
				changesDirection = True
				continue

			changesDirection = True
			lastTransition = time.time()
			turnStrongerLeft()

def turnStrongerLeft():
	doStuffForTurningStrongerLeft
	changesDirection = False

def turnStrongerRight():
	doStuffForTurningStrongerRight
	changesDirection = False

def turn180():
	doStuffForTurning180
	changesDirection = False