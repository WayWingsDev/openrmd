driver =`ls -F | grep -Ev 'specialipc' |  grep /`

libs:
	@cd specialipc; make; cd ..;
	@for file in $(driver); do \
		cd $$file; make; cd ..; \
	done
	
clean:
	@cd specialipc; make clean; cd ..;
	@for file in $(driver); do \
		cd $$file; make clean; cd ..; \
	done
