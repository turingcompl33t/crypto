# Makefile for RSA cryptosystem.

keys:
	python3 keygen.py

	@echo ""
	@echo "Generated RSA Public Key (key.pub):"
	@cat key.pub

	@echo ""
	@echo "Generated RSA Private Key (key.priv):"
	@cat key.priv

# clean without removing keyfiles
clean:
	rm -f *.pyc
	rm -rf __pycache__/

# remove the keyfiles too
cleanall: clean
	rm -f *.pub
	rm -f *.priv

.PHONY: clean cleanall 
